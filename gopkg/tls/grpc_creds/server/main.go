package main

import (
	"context"
	"log"
	"net"

	pb "github.com/warm3snow/workspace/gopkg/tls/grpc/protos"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
)

const (
	port = ":8080"
)

type server struct{}

func (s *server) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloReply, error) {
	log.Printf("Server receive: ", in.Name)
	return &pb.HelloReply{Message: "Hello" + in.Name}, nil
}

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	//tls
	creds, err := credentials.NewServerTLSFromFile("./certs/server.pem", "./certs/server.key")
	if err != nil {
		log.Fatalf("failed to new creds: %v", err)
	}

	s := grpc.NewServer(grpc.Creds(creds))
	pb.RegisterGreeterServer(s, &server{})

	//	reflection.Register(s)

	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
