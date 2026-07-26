package config

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"encoding/json"
)

// Struct to hold values
type Config struct {
	ShowIcons bool `json:"icons"`
	ShowColor bool `json:"color"`
}

// Default config to use
var defaultConfig = Config{
	ShowIcons: true,
	ShowColor: true,
}

// Returns the path of the config file
func configPath() (string, error) {
	// Config Dir:
	// Linux: /home/<username>/.config/lsi/lsi.json
	// MacOS: /Users/<username>/Library/Application Support/lsi/lsi.json
	configDir, err := os.UserConfigDir()
	if err != nil {
		return "", err
	}
	return filepath.Join(configDir, "lsi", "lsi.json"), nil
}

