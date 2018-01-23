package main

import "plugin"

func main() {
	p, err := plugin.Open("plugin.so")
	if err != nil {
		panic(err)
	}

	printName, err := p.Lookup("PrintName")
	if err != nil {
		panic(err)
	}
	printName.(func())()

	sym, err := p.Lookup("PrintKind")
	if err != nil {
		panic(err)
	}
	printKind, ok := sym.(func(t string))
	if !ok {
		panic("Plugin does not implement required function signature for 'PrintKind'")
	}
	printKind("dog")

}
