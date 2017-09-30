package main

import (
	"fmt"

	"github.com/spf13/viper"
)

func main() {
	viper.SetConfigName("core")
	viper.AddConfigPath(".")

	if err := viper.ReadInConfig(); err != nil {
		panic(err)
	}
	var cfg config
	if err := viper.Unmarshal(&cfg); err != nil {
		panic(err)
	}
	fmt.Println(viper.Get("csr.key.algo"), viper.Get("csr.key.size"))
	fmt.Println(viper.AllKeys())
	fmt.Printf("%+v", cfg.Csr.KeyType)
}

type config struct {
	Csr CSR
	Url string
}

type CSR struct {
	KeyType *KeyReq `yaml:"key" json:"key"`
	Cn      string
	Hosts   []string
	Ca      *CaInfo
}

type KeyReq struct {
	Algo string
	Size int
}

type CaInfo struct {
	Pathlen int
	Expiry  int
}
