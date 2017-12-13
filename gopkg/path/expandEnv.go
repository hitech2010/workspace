package main

import (
	"fmt"
	"os"
)

func main() {
	homeDir := os.ExpandEnv("$HOME/.tendermint_test")
	fmt.Println(homeDir)
}
