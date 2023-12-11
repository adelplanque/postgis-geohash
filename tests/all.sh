#/bin/sh

set -xe

./install-check.sh 9.5-2.5
./install-check.sh 9.5-3.0
./install-check.sh 10-2.5
./install-check.sh 10-3.0
./install-check.sh 11-2.5
./install-check.sh 11-3.0
./install-check.sh 12-2.5
./install-check.sh 12-3.0
./install-check.sh 13-3.0
./install-check.sh 13-3.1
./install-check.sh 14-3.4 "llvm15-dev clang15"
./install-check.sh 15-3.4 "llvm15-dev clang15"
./install-check.sh 16-3.4 "llvm15-dev clang15"
