package options

import (
	"fmt"

	"github.com/spf13/pflag"
)

func validate(fs *pflag.FlagSet) error {
	changed := func(name string) bool {
		f := fs.Lookup(name)
		return f != nil && f.Changed
	}

	activeFrom := func(names []string) []string {
		var out []string
		for _, name := range names {
			if changed(name) {
				out = append(out, name)
			}
		}
		return out
	}

	activeDisplay := activeFrom(displayFlags)
	activeConfig := activeFrom(configFlags)

	// If both config is changed
	if changed("enable-icons") && changed("disable-icons") {
		return fmt.Errorf("--enable-icons and --disable-icons can not be chained")
	}
	if changed("enable-color") && changed("disable-color") {
		return fmt.Errorf("--enable-color and --disable-color can not be chained")
	}

	// Version with other flags
	if changed("version") && (len(activeDisplay) > 0 || len(activeConfig) > 0) {
		return fmt.Errorf("--version can not be chained")
	}

	// Config flags with other flags
	if len(activeConfig) > 0 && len(activeDisplay) > 0 {
		return fmt.Errorf("config flags can not be chained")
	}

	// Sort flag conflicts (Only one sort can be applied)
	for flag, bad := range sortFlags {
		if !changed(flag) {
			continue
		}
		for _, bad := range bad {
			if changed(bad) {
				return fmt.Errorf("--%s and --%s can not be chained", flag, bad)
			}
		}
	}

	return nil
}
