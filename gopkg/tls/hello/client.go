package main

import (
	"crypto/tls"
	"fmt"
	"io"
	"log"
	"time"
)

func main() {
	tlsConfig := &tls.Config{}
	tlsConfig.InsecureSkipVerify = false
	tlsConfig.ServerName = "server"
	conn, err := tls.Dial("tcp", ":8888", tlsConfig)
	if err != nil {
		log.Fatalln(err.Error())
	}
	defer conn.Close()

	log.Println("Client connect To ", conn.RemoteAddr().String())
	status := conn.ConnectionState()
	fmt.Printf("%#v\n", status)
	buf := make([]byte, 1024)
	ticker := time.NewTicker(1 * time.Millisecond * 500)

	for {
		select {
		case <-ticker.C:
			{
				_, err := io.WriteString(conn, "hello")
				if err != nil {
					log.Fatalln(err.Error())
				}
				len, err := conn.Read(buf)
				if err != nil {
					fmt.Println(err.Error())
				} else {
					fmt.Println("Receive From Server: ", string(buf[:len]))
				}
			}
		}
	}
}
