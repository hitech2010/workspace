package main

import (
	"context"
	"log"

	pb "github.com/warm3snow/workspace/gopkg/tls/grpc/protos"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
)

const (
	addr = "localhost:8080"
)

func main() {
	var opts []grpc.DialOption
	creds, err := credentials.NewClientTLSFromFile("./certs/server.pem", "www.random.com")
	if err != nil {
		log.Fatalln(err)
	}
	opts = append(opts, grpc.WithTransportCredentials(creds))

	conn, err := grpc.Dial(addr, opts...)
	if err != nil {
		log.Fatalf("failed to Dail: %v", err)
	}
	defer conn.Close()
	c := pb.NewGreeterClient(conn)

	r, err := c.SayHello(context.Background(), &pb.HelloRequest{Name: "bill"})
	if err != nil {
		log.Fatalf("failed to SayHello: %v", err)
	}
	log.Printf("Greeting: %s", r.Message)
}
