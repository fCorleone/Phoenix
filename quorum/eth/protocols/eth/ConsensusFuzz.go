package eth

import (
	"github.com/ethereum/go-ethereum/p2p"
	fuzz "github.com/google/gofuzz"
	"math/rand"
	"time"
)

func (p *Peer) FuzzConsensus() {
	//TODO temp: send mutated tx here!

	time.Sleep(time.Duration(2)*time.Second)		//sleep 2 minutes

	p.Log().Error("Begin sending Fuzzed Consensus!!!!!!!")

	f := fuzz.New().NilChance(0.1)
	for{
		//p.Log().Warn("Sending Fuzzed Message!")
		ConsensusMsgFuzzed(p,f)
		time.Sleep(time.Duration(1)*time.Second)
	}

}


func ConsensusMsgFuzzed(p *Peer, f *fuzz.Fuzzer) error {
	if len(p.ConsensusMsg) == 0{
		return nil
	}else{
		msg := p.ConsensusMsg[rand.Intn(len(p.ConsensusMsg))]
		MutateConsensuss(f, msg)
		return p2p.SendWithNoEncoding(p.consensusRw, 0x11, msg)
		return nil
	}
}


func MutateConsensuss(f *fuzz.Fuzzer, msg []byte){
	f.Fuzz(&msg)
}