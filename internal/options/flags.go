package options

import (
	"fmt"
	"os"

	"github.com/spf13/pflag"
)

// Struct to hold the state of input (flags and path)
type Options struct {
	Path string
	// Version
	ShowVersion bool
	// Display
	ShowHidden   bool
	ShowDetailed bool
	OnePerLine   bool
	// Sort
	ReverseSort bool
	SortBySize  bool
	SortByDate  bool
	// Temp
	NoColor bool
	NoIcon  bool
	// Config
	EnableIcons  bool
	DisableIcons bool
	EnableColor  bool
	DisableColor bool
}

// display-affecting flags — config/version flags can't mix with these.
var displayFlags = []string{
	"all", "long", "one-line", "reverse", "size", "time", "no-color", "no-icon",
}

// config-affecting flags — mutually exclusive with display flags and version.
var configFlags = []string{
	"enable-icons", "disable-icons", "enable-color", "disable-color",
}

var sortFlags = map[string][]string{
	"size": {"time"},
	"time": {"size"},
}

func Parse() Options {
	var opts Options
	// Basic flags
	pflag.BoolVarP(&opts.ShowVersion, "version", "v", false, "Show version info")
	pflag.BoolVarP(&opts.ShowHidden, "all", "a", false, "Show hidden files")
	pflag.BoolVarP(&opts.ShowDetailed, "long", "l", false, "Detailed view")
	pflag.BoolVarP(&opts.OnePerLine, "one-line", "1", false, "One entry per line")
	pflag.BoolVarP(&opts.ReverseSort, "reverse", "r", false, "Reverse the order")
	pflag.BoolVarP(&opts.SortBySize, "size", "s", false, "Sort by size")
	pflag.BoolVarP(&opts.SortByDate, "time", "t", false, "Sort by date modified")
	// Temp
	pflag.BoolVar(&opts.NoColor, "no-color", false, "Temporarily disable colors")
	pflag.BoolVar(&opts.NoIcon, "no-icon", false, "Temporarily disable icons")
	// Config
	pflag.BoolVar(&opts.EnableIcons, "enable-icons", false, "Persist: enable icons in config")
	pflag.BoolVar(&opts.DisableIcons, "disable-icons", false, "Persist: disable icons in config")
	pflag.BoolVar(&opts.EnableColor, "enable-color", false, "Persist: enable color in config")
	pflag.BoolVar(&opts.DisableColor, "disable-color", false, "Persist: disable color in config")

	pflag.Parse()

	// Resolves flag conflicts
	if err := validate(pflag.CommandLine); err != nil {
		fmt.Fprintf(os.Stderr, "lsi: error: %s\n", err)
		os.Exit(1)
	}

	// Path resolution
	opts.Path = "."
	if pflag.NArg() > 0 {
		opts.Path = pflag.Arg(0)
	}

	return opts
}
