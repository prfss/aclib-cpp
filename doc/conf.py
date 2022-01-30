#!/usr/bin/env python3
# -*- coding: utf-8 -*-

extensions = ['sphinx.ext.mathjax', 'sphinx.ext.githubpages']

templates_path = ['_templates']

source_suffix = '.rst'

master_doc = 'index'

project = 'acl-ext'
author = 'sash0'
html_show_copyright = False

version = ''
release = ''

language = 'ja'

exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

pygments_style = 'sphinx'

todo_include_todos = False

html_theme = 'sphinx_rtd_theme'

html_theme_options = {}

html_static_path = []

htmlhelp_basename = 'acl-extdoc'

latex_elements = {}

latex_documents = [
    (master_doc, 'acl-ext.tex', 'acl-ext Documentation',
     'sash0', 'manual'),
]

man_pages = [
    (master_doc, 'acl-ext', 'acl-ext Documentation',
     [author], 1)
]

texinfo_documents = [
    (master_doc, 'acl-ext', 'acl-ext Documentation',
     author, 'acl-ext', '',
     'Miscellaneous'),
]

rst_prolog = """
:github_url: https://github.com/prfss/acl-ext
"""
