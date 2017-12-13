package main

import (
	"crypto/rand"
	"crypto/tls"
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	crt, err := tls.LoadX509KeyPair("server.crt", "server.key")
	if err != nil {
		log.Fatalln(err.Error())
	}
	tlsConfig := &tls.Config{}
	tlsConfig.Certificates = []tls.Certificate{crt}
	tlsConfig.Time = time.Now
	tlsConfig.Rand = rand.Reader

	l, err := tls.Listen("tcp", ":8888", tlsConfig)
	if err != nil {
		log.Fatalln(err.Error())
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println(err.Error())
			continue
		}
		go HandleClientConn(conn)

	}
}

func HandleClientConn(conn net.Conn) {
	defer conn.Close()
	fmt.Println("Receive connect From ", conn.RemoteAddr().String())
	var buf []byte
	for {
		len, err := conn.Read(buf)
		if err != nil {
			log.Println(err.Error())
			break
		}
		fmt.Printf("Receive Data: %s\n", string(buf[:len]))
		_, err = conn.Write([]byte("Server received Data:" + string(buf[:len])))
		if err != nil {
			break
		}
	}
	fmt.Println("Client ", conn.RemoteAddr().String()+"Connection Closed...")
}
