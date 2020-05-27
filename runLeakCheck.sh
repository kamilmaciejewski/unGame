#!/bin/bash
valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=valgrind_ignore Default/unGame --mode console
