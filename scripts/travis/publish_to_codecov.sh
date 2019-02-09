#!/bin/bash

set -ev

# publish to codecov
export CODECOV_TOKEN="fc820b41-816f-4dfa-b7fb-1842488e3a53"
bash <(curl -s https://codecov.io/bash)
