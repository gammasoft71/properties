#!/bin/bash

set -ev

# publish to codecov
export CODECOV_TOKEN="dc574c52-8843-42a2-b2fe-5d58506b41d0"
bash <(curl -s https://codecov.io/bash)
