package main

import "path/filepath"

func main() {
	path, _ := filepath.Abs("./1.txt")
	println(path)
	println(filepath.Base("./1.txt"))
	println(filepath.Join("c:/a", "b", "/c"))
	println(filepath.Clean("C:/a/b/../c"))
}
