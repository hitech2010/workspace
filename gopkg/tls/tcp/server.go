package main

import (
	"bufio"
	"crypto/tls"
	"log"
	"net"
)

func printErr(err error) {
	if err != nil {
		log.Println(err.Error())
	}
}

func main() {
	cert, err := tls.LoadX509KeyPair("certs/server.pem", "certs/server.key")
	printErr(err)

	tlsConfig := &tls.Config{Certificates: []tls.Certificate{cert}}
	ln, err := tls.Listen("tcp", ":8080", tlsConfig)
	printErr(err)
	defer ln.Close()

	for {
		conn, err := ln.Accept()
		if err != nil {
			printErr(err)
			continue
		}
		go handleConn(conn)
	}

}

func handleConn(conn net.Conn) {
	defer conn.Close()
	r := bufio.NewReader(conn)
	for {
		msg, err := r.ReadString('\n')
		if err != nil {
			printErr(err)
			return
		}
		println(msg)

		n, err := conn.Write([]byte("world\n"))
		if err != nil {
			log.Println(n, err)
			return
		}
	}
}
