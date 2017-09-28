package main

import (
	"flag"
	"log"
	"os"
	"testing"
)

var wordPtr = flag.String("word", "foo", "a string")

func TestMain(m *testing.M) {
	flag.Parse()
	log.Println("[TestMain] word:", *wordPtr)

	log.Println("[TestMain] before run()")
	code := m.Run()
	log.Println("[TestMain] after run()")

	os.Exit(code)
}

func Test1(t *testing.T) {
	log.Println("[Test1] running ", *wordPtr)
}
