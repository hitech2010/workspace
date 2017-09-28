package main

import "fmt"
import "os"

func main() {
	err := os.Chdir("/home/hxy")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	dir, err := os.Open(".")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	names, _ := dir.Readdirnames(-1)
	for _, name := range names {
		fmt.Println(name)
	}
}
