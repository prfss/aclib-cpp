#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import json
from pathlib import Path
import re
from typing import Optional, Tuple, List, Pattern

CUT_BEGIN_RE: Pattern = re.compile(r"^\s*//\s*<---")
CUT_END_RE: Pattern = re.compile(r"^\s*//\s*--->")
NAME_RE: Pattern = re.compile(r"^\s*//\s*name:(.+)")


def parse(block: List[str]) -> Optional[Tuple[str, str, List[str]]]:
    name = None
    prefix = None
    main_part = []
    for line in block:
        match = NAME_RE.match(line)
        if match:
            name = match.group(1).strip()
            prefix = name.lower()
        else:
            main_part.append(line)

    if name is None or prefix is None:
        return None
    else:
        return name, prefix, main_part


def extract(source_code: str) -> List[Tuple[str, str, List[str]]]:
    in_block = False
    block_list = []
    block: List[str] = []
    for s in source_code.splitlines():
        if CUT_BEGIN_RE.match(s):
            block = []
            in_block = True
        elif CUT_END_RE.match(s):
            if in_block:
                block_list.append(block)
                in_block = False
        elif in_block:
            block.append(s)

    return list(filter(None, map(parse, block_list)))


def usage() -> None:
    print(f"Usage: python {sys.argv[0]} <directory> <outputfile>", file=sys.stderr)
    sys.exit(1)


def main() -> None:
    if len(sys.argv) != 3:
        usage()

    directory = Path(sys.argv[1]).resolve()

    if not directory.is_dir():
        print(f"{directory.name} is not a directory", file=sys.stderr)

    outfile = Path(sys.argv[2]).resolve()

    snippet = dict()
    try:
        for file in directory.iterdir():
            if file.is_file() and file.suffix == ".hpp":
                with open(file, "r") as f:
                    source_code = f.read()
                    extracted = extract(source_code)
                    for [name, prefix, code] in extracted:
                        print(
                            f"Extracted {name} ({len(''.join(code))} character(s)) from {file.name}"
                        )
                        stem = file.stem
                        item = dict({"scope": "cpp", "prefix": [prefix], "body": code})
                        name = f"{name} (aclext:{stem})"
                        if name in snippet:
                            print(
                                f"Snippet '{name}' already exists. New one is skipped"
                            )
                        else:
                            snippet[name] = item

        output = json.dumps(snippet, indent=4)

        with open(outfile, "w") as f:
            f.write(output)

        print(f"Saved to {outfile}")

    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
