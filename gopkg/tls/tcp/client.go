package main

import (
	"crypto/tls"
	"log"
)

func main() {
	conf := &tls.Config{
		InsecureSkipVerify: true,
	}
	conn, err := tls.Dial("tcp", "localhost:8080", conf)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()

	n, err := conn.Write([]byte("hello\n"))
	if err != nil {
		log.Println(err)
		return
	}
	buf := make([]byte, 100)
	n, err = conn.Read(buf)
	if err != nil {
		log.Println(err)
		return
	}

	println(string(buf[:n]))
}
