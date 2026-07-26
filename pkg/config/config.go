package config

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
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

// Helper function to reset defaults if missing or corrupted config file
func resetDefault() (*Config, error) {
	cfg := defaultConfig
	if err := SaveConfig(&cfg); err != nil {
		return nil, err
	}
	return &cfg, nil
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
