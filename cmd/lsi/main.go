package main

import (
	"fmt"
	"os"
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
		// Tree
		treeDepth int
		// Temporary
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
	// Tree flags
	flag.IntVarP(&treeDepth, "tree", "", 0, "Tree view with optional depth (default depth 1)")
	flag.Lookup("tree").NoOptDefVal = "1" // Defaults to 1
	// Temporary flags
	flag.BoolVarP(&noColor, "no-color", "", false, "Temporarily disable colors")
	flag.BoolVarP(&noIcon, "no-icon", "", false, "Temporarily disable icons")
	// Config flags
	flag.StringVar(&setIcon, "set-icon", "", "Set icon state in config")
	flag.StringVar(&setColor, "set-color", "", "Set color state in config")

	flag.Parse()

	// Handle Configs
	if flag.CommandLine.Changed("set-icon") || flag.CommandLine.Changed("set-color") {
		if flag.CommandLine.Changed("set-icon") {

		}
		if flag.CommandLine.Changed("set-color") {

		}
		os.Exit(0)
	}

	// Tree Mode
	isTreeMode := flag.CommandLine.Changed("tree")
	hasConflict := showDetailed || onePerLine || reverseSort || sortBySize || sortByDateModified

	if isTreeMode && hasConflict {
		fmt.Fprintln(os.Stderr, "lsi: error: tree view (--tree): Incompatible flag combinations.")
		fmt.Fprintln(os.Stderr, "Try 'lsi --help' for more information.")
		os.Exit(1)
	}
	if treeDepth < 1 {
		
	}
}
