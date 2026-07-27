package main

import (
	"fmt"
	"os"
	"github.com/Rajdeep-Nemo/lsi/internal/config"
	"github.com/spf13/pflag"
)

func main() {
	// Handle Config Changes
	if pflag.CommandLine.Changed("set-icon") || pflag.CommandLine.Changed("set-color") {
		if pflag.CommandLine.Changed("set-icon") {
			config.SetOptions("icons", setIcon)
		}
		if pflag.CommandLine.Changed("set-color") {
			config.SetOptions("color", setColor)
		}
		os.Exit(0)
	}
	
	// Gets configs from config file
	cfg, err := config.LoadConfig()
	if err != nil {
		os.Exit(0)
	}
	fmt.Println(cfg.ShowIcons)
}
