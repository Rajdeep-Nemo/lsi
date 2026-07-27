package options

import (
	"github.com/spf13/pflag"
)
// Struct to hold the state of input (flags and path)
type Options struct {
	Path string

	ShowHidden   bool
	ShowDetailed bool
	OnePerLine   bool

	ReverseSort bool
	SortBySize  bool
	SortByDate  bool

	NoColor bool
	NoIcon  bool

	SetIcon  bool
	SetColor bool
}

func Parse() Options {
	var opts Options
	// Basic flags
	pflag.BoolVarP(&opts.ShowHidden, "", "a", false, "Show hidden files")
	pflag.BoolVarP(&opts.ShowDetailed, "", "l", false, "Detailed view")
	pflag.BoolVarP(&opts.OnePerLine, "", "1", false, "One entry per line")
	pflag.BoolVarP(&opts.ReverseSort, "", "r", false, "Reverse the order")
	pflag.BoolVarP(&opts.SortBySize, "", "s", false, "Sort by size")
	pflag.BoolVarP(&opts.SortByDate, "", "t", false, "Sort by date modified")
	// Temporary flags
	pflag.BoolVar(&opts.NoColor, "no-color", false, "Temporarily disable colors")
	pflag.BoolVar(&opts.NoIcon, "no-icon", false, "Temporarily disable icons")
	// Config flags
	pflag.BoolVar(&opts.SetIcon, "set-icon", true, "Set icon state in config")
	pflag.BoolVar(&opts.SetColor, "set-color", true, "Set color state in config")

	pflag.Parse()

	// Path resolution
	opts.Path = "."
	if pflag.NArg() > 0 {
		opts.Path = pflag.Arg(0)
	}

	return opts
}
