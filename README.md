# BixCoin V1.0.0 AFR


Intro
-----
BixCoin is a free open source project derived from Bitcoin, with
the goal of providing a long-term energy-efficient scrypt-based crypto-currency.
Built on the foundation of Bitcoin, PPCoin and NovaCoin, innovations such as proof-of-stake
help further advance the field of crypto-currency.


UNIX BUILD NOTES
====================

To Build Headless 

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils

sudo apt-get install qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools build-essential libboost-dev libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libminiupnpc-dev 

sudo apt-get install software-properties-common

sudo add-apt-repository ppa:bitcoin/bitcoin

sudo apt-get update

sudo apt-get install libdb4.8-dev libdb4.8++-dev

sudo apt-get install libqrencode-dev


git clone https://github.com/Project-Bix/BixCoin.git

cd BixCoin/src/secp256k1

chmod +x autogen.sh

./autogen.sh

./configure

make && make install

cd

cd BixCoin/src

sudo make -f makefile.unix



Copyright (c) 2017 - 2018 BixCoin Developers
Distributed under the MIT/X11 software license, see the accompanying
file license.txt or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in
the OpenSSL Toolkit (http://www.openssl.org/).  This product includes
cryptographic software written by Eric Young (eay@cryptsoft.com).