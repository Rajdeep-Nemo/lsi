package main

import (
	"fmt"
	"os"
	"github.com/Rajdeep-Nemo/lsi/pkg/config"
	"github.com/spf13/pflag"
)

func main() {
	// flag variables
	var (
		// Basics
		showHidden         bool
		showDetailed       bool
		onePerLine         bool
		reverseSort        bool
		sortBySize         bool
		sortByDateModified bool
		// Temporary styling
		noColor bool
		noIcon  bool
		// Config
		setIcon  bool
		setColor bool
	)
	// Basic flags
	pflag.BoolVarP(&showHidden, "", "a", false, "Show hidden files")
	pflag.BoolVarP(&showDetailed, "", "l", false, "Detailed view")
	pflag.BoolVarP(&onePerLine, "", "1", false, "One entry per line")
	pflag.BoolVarP(&reverseSort, "", "r", false, "Reverse the order")
	pflag.BoolVarP(&sortBySize, "", "s", false, "Sort by size")
	pflag.BoolVarP(&sortByDateModified, "", "t", false, "Sort by date modified")
	// Temporary flags
	pflag.BoolVarP(&noColor, "no-color", "", false, "Temporarily disable colors")
	pflag.BoolVarP(&noIcon, "no-icon", "", false, "Temporarily disable icons")
	// Config flags
	pflag.BoolVar(&setIcon, "set-icon", true, "Set icon state in config")
	pflag.BoolVar(&setColor, "set-color", true, "Set color state in config")

	pflag.Parse()

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

	// Path resolution
	targetPath := "."
	// If argument is present after path resolution consider that as path
	if pflag.NArg() > 0 {
		targetPath = pflag.Arg(0)
	}
	
	// Gets configs from config file
	cfg, err := config.LoadConfig()
	if err != nil {
		os.Exit(0)
	}
	fmt.Println(cfg.ShowIcons)
}
