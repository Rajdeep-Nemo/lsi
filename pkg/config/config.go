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

func initConfig() error {
	// gets the path
	path, err := configPath()
	if err != nil {
		return err
	}
	// Creates the config directory
	if err := os.MkdirAll(filepath.Dir(path), 0755); err != nil {
		return err
	}
	// Create the config file if not present
	if _, err := os.Stat(path); err == nil {
		return nil
	} else if os.IsNotExist(err) {
		return err
	}
}

func loadConfig() {

}

func handleConfigChange(key, value string) {
	if value != "true" && value != "false" {
		fmt.Fprintf(os.Stderr, "lsi: invalid value '%s' for --set-%s\n", value, key)
		os.Exit(1)
	}
	// config.Save(...)
}