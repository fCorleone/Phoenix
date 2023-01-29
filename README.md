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



**Quorum**



## Phoenix for FISCO-BCOS

### prerequisites

Set a 10-node fisco-bcos group by referring https://fisco-bcos-documentation.readthedocs.io/en/latest/docs/installation.html

### setup LOKI testnet & start testing

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



## Phoenix for Quorum
