# Phoenix
A framework for detecting and positioning the resilience issues of consortium blockchain. 

## Code Structure

The code is organized as three directories. For each directory, it contains the source code of the consortium blockchain as well as Phoenix.

**FISCO-BCOS**

In the directory FISCO-BCOS, it contains the source code of FISCO-BCOS 3.1.0. While the directory `phoneix-test` contains the source code of Phoenix that adapts to FISCO-BCOS.

- File `PhoenixCoordinator.cpp/PhoenixCoordinator.h` describes how the coordinator of Phoenix works during the testing. 

- While file `PhoenixHookPosition.cpp/PhoenixHookPosition.h` contains the hook position definition of Phoenix in FISCO-BCOS. 

- And the file `UnderlyingChaos.cpp/UnderlyingChaos.h` defines several functions for the chaos strategies.

**Hyperledger Fabric**
In the directory fabric, it contains the source code of smartbft version of fabric as well as the source code of Phoenix that adapts to Fabric 1.4.0.

- File `blockprovider/blockprovider.go` and `committer/committer_impl.go` contain the block related chaos strategies.

- And File `orderer/consensus/smartbft/*fuzz.go` defines several functions for consensus related chaos stragegies.

-- All hook position of Phoenix in Fabric are instructmented into the `blockdeliver.go`, `broadcast.go` and `chain.go`.


**Quorum**
In the directory quorum, it contains the source code of qbft version of quorum as well as the source code of Phoenix that adapts to quorum 1.10.

- File `eth/protocol/broadcast.go` and `qbft/core/commit.go` contain the block related chaos strategies.

- And File `eth/protocols/eth/*fuzz.go` defines several functions for consensus related chaos stragegies.

-- All hook position of Phoenix in Fabric are instructmented into the `eth/protocol/peer.go`, `eth/protocol/broadcast.go` and `eth/protocol/sync.go`.


## Phoenix for FISCO-BCOS

### prerequisites

Set a 10-node fisco-bcos group by referring https://fisco-bcos-documentation.readthedocs.io/en/latest/docs/installation.html

### setup Phoenix testnet & start testing

```bash
bash build_chain.sh -l 127.0.0.1:10 -p 30300,20200,8545
```

This will setup a 10-node group locally, change 3 of the nodes to the chaos node:

```bash
# Change the start.sh and stop.sh of node0, node1 and node2 to:
fisco_bcos=Phoenix/fisco/bin/fisco-bcos # this is the binary compiled by the chain code with phoenix test libraries.
```

Then use the start-all shell to start the chain nodes:

```bash
cd nodes
./start_all.sh
```

Finally, just start the phoenix coordinator by:

```shell
bash build/phoneix-test/phoenix
```



To trigger the transactions of FISCO-BCOS network, one can reffer to this documentation: https://fisco-bcos-documentation.readthedocs.io/zh_CN/latest/docs/tutorial/stress_testing.html  and start the stress testing program for the group.



## Phoenix for Hyperledger Fabric

### prerequisites
Setup fabric network environment, can be found in https://hyperledger-fabric.readthedocs.io/en/release/prereqs.html.

### build phoenix-fabric image
```bash
cd fabric
make orderer
make docker-orderer
```
rename the docker image to `smartbft/fabric-orderer-phoenix:latest`.

### setup Phoenix testnet 

```bash
cd fabric/first-network
vim byfn.sh
replace fabric-orderer:latest with fabric-orderer-phoenix
```

### start chaos testing
```bash
cd fabric/first-network
./byfn generate
./byfn up
./byfn down
```

Finally, just start the phoenix coordinator by:
```bash
./byfn phoenix
```


## Phoenix for Quorum

### prerequisites
Setup go-quorum qbft network environment, can be found in https://consensys.net/docs/goquorum/en/latest/tutorials/private-network/create-qbft-network/.

### build geth-phonex
```bash
cd quorum/chaostest
make geth
rename build/bin/geth build/bin/geth-phonex
```

### setup Phoenix testnet & start fuzzing

```bash
mkdir quorum/chaostest
cd quorum/chaostest
```
#### setup bootnode
```bash
../bin/bootnode -genkey bootnode.key
../bin/bootnode -nodekey bootnode.key
```
#### initialize node
```bash
mkdir -p Node-0/data/keystore Node-1/data/keystore Node-2/data/keystore Node-3/data/keystore Node-4/data/keystore ... Node-n/data/keystore
```
#### run tyr-geth node

##### node1
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth-phonex --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22000 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32000 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30300
 ```
 
 ##### node2
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth-phonex --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22001 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32001 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30301
 ```

##### node3
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth-phonex --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints
    --http --http.addr 127.0.0.1 --http.port 22002 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32002--ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30302
 ```
 
##### node4
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22003 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32003 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30303
 ```
 
##### node5
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22004 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32004 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30304
 ```
 #### ...

#### node_n
similar to previous nodes.


Finally, just start the phoenix coordinator by:
```bash
geth-phonex --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22004 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32004 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30304 \
	--condinator phoenix-condinator
```




## Phoenix for Geth

### prerequisites
Setup geth network environment, can be found in https://priyalwalpita.medium.com/setting-up-the-go-ethereum-geth-environment-in-ubuntu-linux-67c09706b42.

### build geth-phoenix
```bash
cd geth/chaostest
make geth
rename build/bin/geth build/bin/geth-phoenix
```

### setup Phoenix testnet & start fuzzing

```bash
mkdir geth/chaostest
cd geth/chaostest
```
#### setup bootnode
```bash
../bin/bootnode -genkey bootnode.key
../bin/bootnode -nodekey bootnode.key
```
#### initialize node
```bash
mkdir -p Node-0/data/keystore Node-1/data/keystore Node-2/data/keystore Node-3/data/keystore Node-4/data/keystore ... Node-n/data/keystore
```
#### run geth-phoenix node


##### node1
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22000 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32000 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30300
 ```
 
 ##### node2
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22001 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32001 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30301
 ```

##### node3
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints
    --http --http.addr 127.0.0.1 --http.port 22002 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32002--ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30302
 ```
 
##### node4
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22003 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32003 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30303
 ```
 
##### node5
```bash
export ADDRESS=$(grep -o '"address": *"[^"]*"' ./data/keystore/accountKeystore | grep -o '"[^"]*"$' | sed 's/"//g')
export PRIVATE_CONFIG=ignore
geth --datadir data \
    --networkid 1337 --nodiscover --verbosity 5 \
    --syncmode full --nousb \
    --istanbul.blockperiod 5 --mine --miner.threads 1 --miner.gasprice 0 --emitcheckpoints \
    --http --http.addr 127.0.0.1 --http.port 22004 --http.corsdomain "*" --http.vhosts "*" \
    --ws --ws.addr 127.0.0.1 --ws.port 32004 --ws.origins "*" \
    --http.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --ws.api admin,trace,db,eth,debug,miner,net,shh,txpool,personal,web3,quorum,istanbul,qbft \
    --unlock ${ADDRESS} --allow-insecure-unlock --password ./data/keystore/accountPassword \
    --port 30304
 ```



## Phoenix for BSC

### prerequisites
Setup BSC network environment, can be found in https://docs.bnbchain.org/docs/getting-started.

### build bsc-phoenix
```bash
cd bsc/chaostest
make bsc
rename build/bin/geth build/bin/bsc-phoenix
```

### setup Phoenix testnet & start fuzzing

```bash
bsc bsc/chaostest
cd geth/chaostest
```
#### setup bootnode
```bash
../bin/bootnode -genkey bootnode.key
../bin/bootnode -nodekey bootnode.key
```
#### initialize node
```bash
for i in 1 2 3 4 5 6 7 8 9 10; do ../bin/geth --datadir ./node$i account new; done

for i in 1 2 3 4 5 6 7 8 9 10; do echo $i > priv/node$i/node$i.pass; done

for i in 1 2 3 4 5 6 7 8 9 10; do ../bin/geth --datadir node$i init genesis.json; done
```
#### run geth-phoenix node


##### node1
```bash
./geth-phoenix --config ./config.toml --datadir ./node1  --cache 8000 --rpc.allow-unprotected-txs --txlookuplimit 0 --tries-verify-mode none
 ```
 
 ##### node2
```bash
./geth-phoenix --config ./config.toml --datadir ./node2  --cache 8000 --rpc.allow-unprotected-txs --txlookuplimit 0 --tries-verify-mode none
 ```

##### node3
```bash
./geth --config ./config.toml --datadir ./node3  --cache 8000 --rpc.allow-unprotected-txs --txlookuplimit 0 --tries-verify-mode none
 ```
 
##### node4
```bash
./geth --config ./config.toml --datadir ./node4  --cache 8000 --rpc.allow-unprotected-txs --txlookuplimit 0 --tries-verify-mode none
 ```
 
##### node5
```bash
./geth --config ./config.toml --datadir ./node5  --cache 8000 --rpc.allow-unprotected-txs --txlookuplimit 0 --tries-verify-mode none
 ```

 

