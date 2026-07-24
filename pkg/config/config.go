package config

import (
	"fmt"
	"os"
	"path/filepath"
)

type config struct {
	showIcons bool
	showColor bool
}

const defaultConfig = `icons=true
color=true
`

// Returns the path of the config file
func configPath() (string, error) {
	configDir, err := os.UserConfigDir()
	if err != nil {
		return "", err
	}
	return filepath.Join(configDir, "lsi", "lsi.conf"), nil
}

