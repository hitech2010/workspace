package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
	"log"
)

func main() {
	//load client key and cert
	cert, err := tls.LoadX509KeyPair("certs/client.pem", "certs/client.key")
	if err != nil {
		log.Println(err)
		return
	}
	//load server cert
	certBytes, err := ioutil.ReadFile("certs/server.pem")
	if err != nil {
		panic("unable to read server.pem")
	}
	certPool := x509.NewCertPool()
	if ok := certPool.AppendCertsFromPEM(certBytes); !ok {
		panic("failed to parse root certificate")
	}

	config := &tls.Config{
		Certificates:       []tls.Certificate{cert}, //client key and cert
		RootCAs:            certPool,                //certificate pool,  include server' cert
		InsecureSkipVerify: true,                    //skip verifying the server and hostname, but verify the signature.
	}

	conn, err := tls.Dial("tcp", "localhost:8080", config)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()
	n, err := conn.Write([]byte("hello\n"))
	if err != nil {
		log.Println(n, err)
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
