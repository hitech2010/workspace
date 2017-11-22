package main

import "testing"
import "crypto/aes"

func BenchmarkAes(b *testing.B) {
	var src, dst, key []byte
	src = []byte("hello bill")
	key = []byte("key")
	block, err := aes.NewCipher(key)
	if err != nil {
		b.Fatal(err)
	}
	for i := 0; i < b.N; i++ {
		block.Encrypt(dst, src)
	}
}
