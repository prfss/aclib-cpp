#! /bin/python3
# -*- coding: utf-8 -*-

import sys
import json
import os
from pathlib import Path
import re
from typing import Optional


def extract(source_code: str) -> Optional[str]:
    res = re.search(r"namespace\s+aclext\s+\{.+\}", source_code, re.DOTALL)
    return res.group(0) if res else None


def capitalize(x: str) -> str:
    return x.capitalize()


def name(file_stem: str) -> str:
    res = " ".join(map(capitalize, re.split(r"[-_]", file_stem)))
    return res + " (aclext)"


def prefix(file_stem: str) -> str:
    return re.sub(r"[-_]", " ", file_stem)


def usage():
    print(f"Usage: python {sys.argv[0]} <directory> <outputfile>")
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
                    if extracted is not None:
                        print(
                            f"Extracted {len(extracted)} character(s) from {file}", file=sys.stderr)
                        stem = Path(file).stem
                        item = dict(
                            {
                                "scope": "cpp",
                                "prefix": [stem],
                                "body": extracted.split("\n")
                            }
                        )
                        snippet[name(stem)] = item

        output = json.dumps(snippet, indent=4)

        with open(outfile, "w") as f:
            f.write(output)

        print(f"Saved to {outfile}")

    except Exception as e:
        print(e, file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
