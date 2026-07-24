package main

import (
	"fmt"
	"os"
	"github.com/Rajdeep-Nemo/lsi/pkg/config"
	flag "github.com/spf13/pflag"
)

func main() {
	// Flag variables
	var (
		// Basic
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
		setIcon  string
		setColor string
	)
	// Basic flags
	flag.BoolVarP(&showHidden, "", "a", false, "Show hidden files")
	flag.BoolVarP(&showDetailed, "", "l", false, "Detailed view")
	flag.BoolVarP(&onePerLine, "", "1", false, "One entry per line")
	flag.BoolVarP(&reverseSort, "", "r", false, "Reverse the order")
	flag.BoolVarP(&sortBySize, "", "s", false, "Sort by size")
	flag.BoolVarP(&sortByDateModified, "", "t", false, "Sort by date modified")
	// Temporary flags
	flag.BoolVarP(&noColor, "no-color", "", false, "Temporarily disable colors")
	flag.BoolVarP(&noIcon, "no-icon", "", false, "Temporarily disable icons")
	// Config flags
	flag.StringVar(&setIcon, "set-icon", "", "Set icon state in config")
	flag.StringVar(&setColor, "set-color", "", "Set color state in config")

	flag.Parse()

	// Handle Configs (Temporary)
	if flag.CommandLine.Changed("set-icon") || flag.CommandLine.Changed("set-color") {
		if flag.CommandLine.Changed("set-icon") {

		}
		if flag.CommandLine.Changed("set-color") {

		}
		os.Exit(0)
	}
	
	// Path resolution
	targetPath := "."
	// If argument is present after path resolution consider that as path
	if flag.NArg() > 0 {
		targetPath = flag.Arg(0)
	}

	// Gets configs from config file
	
	
}
