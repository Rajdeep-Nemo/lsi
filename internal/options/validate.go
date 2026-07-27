package options

import "errors"

func Validate(opts Options) error {
	// Config flags cannot be combined with listing flags.
	if (opts.SetIcon || opts.SetColor) &&
		(opts.ShowHidden ||
			opts.ShowDetailed ||
			opts.OnePerLine ||
			opts.ReverseSort ||
			opts.SortBySize ||
			opts.SortByDate ||
			opts.NoColor ||
			opts.NoIcon) {

		return errors.New("configuration flags cannot be combined with listing flags")
	}
}
