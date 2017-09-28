package main

import (
	"fmt"
	"math/big"
	"testing"
)

func BenchmarkLoops(b *testing.B) {
	for i := 0; i < b.N; i++ {
		fmt.Sprintf("hello %d", i)
	}
}

func BenchmarkBigLen(b *testing.B) {
	big := new(big.Int)
	big = big.MulRange(1, 10)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		big.BitLen()
	}
}
