package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Println(os.TempDir())
	fmt.Println(os.Getenv("PWD"))
}
