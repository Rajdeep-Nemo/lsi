package config

import (
	"fmt"
	"os"
	"path/filepath"
)

// Struct to hold values
type Config struct {
	showIcons bool
	showColor bool
}

// Default config to use
const defaultConfig = `icons=true
color=true
`

// Returns the path of the config file
func configPath() (string, error) {
	// Config Dir:
	// Linux: /home/<username>/.config/lsi/lsi.conf
	// MacOS: /Users/<username>/Library/Application Support/lsi/lsi.conf
	configDir, err := os.UserConfigDir()
	if err != nil {
		return "", err
	}
	return filepath.Join(configDir, "lsi", "lsi.conf"), nil
}

// Initializes the config for the first time or if the file is corrupted
func initConfig() error {
	// gets the path
	path, err := configPath()
	if err != nil {
		return err
	}
	// Creates the config directory if not already
	if err := os.MkdirAll(filepath.Dir(path), 0755); err != nil {
		return err
	}
	// If the file exist return nil
	if _, err := os.Stat(path); err == nil {
		return nil
	}
	// If file doesn't exist, write defaultConfig
	return os.WriteFile(path, []byte(defaultConfig), 0644)
}

// Reads and parses the config into the struct
func loadConfig() (*Config, error){
	
}

func handleConfigChange(key, value string) {
	if value != "true" && value != "false" {
		fmt.Fprintf(os.Stderr, "lsi: invalid value '%s' for --set-%s\n", value, key)
		os.Exit(1)
	}
	// config.Save(...)
}