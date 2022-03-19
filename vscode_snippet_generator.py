#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import json
import os
from pathlib import Path
import re
from typing import Optional, Tuple

CUT_BEGIN = r"^\s*//\s*<---"
CUT_END = r"^\s*//\s*--->"
NAME = r"^\s*//\s*name:(.+)"


def parse(code: [str]) -> Optional[Tuple[str, str, str]]:
    name = None
    prefix = None
    main_part = []
    for line in code:
        m = re.match(NAME, line)
        if m:
            name = m.group(1).strip()
            prefix = name.lower()
        else:
            main_part.append(line)

    if name is None or prefix is None:
        return None
    else:
        return name, prefix, main_part


def extract(source_code: str) -> [Tuple[str, str, str]]:
    cut = False
    codes = []
    code = []
    for s in source_code.splitlines():
        if re.match(CUT_BEGIN, s):
            code = []
            cut = True
        elif re.match(CUT_END, s):
            if cut:
                codes.append(code)
                cut = False
        elif cut:
            code.append(s)

    return list(filter(None, map(parse, codes)))


def usage():
    print(f"Usage: python {sys.argv[0]} <directory> <outputfile>", file=sys.stderr)
    sys.exit(1)


def main():
    if len(sys.argv) != 3:
        usage()

    [directory, outfile] = sys.argv[1:]
    snippet = dict()
    try:
        def absolute(file: str) -> str:
            return os.path.join(directory, file)

        files = (file for file in map(absolute, os.listdir(directory))
                 if os.path.isfile(file))

        for file in files:
            if file.endswith(".hpp"):
                with open(file, "r") as f:
                    source_code = f.read()
                    extracted = extract(source_code)
                    for [name, prefix, code] in extracted:
                        print(
                            f"Extracted {name} ({len(''.join(code))} character(s)) from {file}")
                        stem = Path(file).stem
                        item = dict(
                            {
                                "scope": "cpp",
                                "prefix": [prefix],
                                "body": code
                            }
                        )
                        name = f"{name} (aclext:{stem})"
                        if name in snippet:
                            print(
                                f"Snippet '{name}' already exists. New one is skipped")
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
