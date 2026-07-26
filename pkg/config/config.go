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

// Saves the config to disk
func SaveConfig(cfg *Config) error {
	// Gets the path
	path, err := configPath()
	if err != nil{
		return err
	}
	// Creates the directory if needed
	if err := os.MkdirAll(filepath.Dir(path), 0755); err != nil {
		return err
	}
	// Format the json data
	data, err := json.MarshalIndent(cfg, "", "    ")
	if err != nil {
		return err
	}
	// Writes back to disk
	return os.WriteFile(path, data, 0644)
}

// Load the config
func LoadConfig() (*Config, error){
	// Gets the path
	path, err := configPath()
	if err != nil {
		return nil,err
	}
	// Gets the data, if file is missing writes default
	data, err := os.ReadFile(path)
	if err != nil {
		return resetDefault()
	}
	// Reads the json data, if file is missing writes default
	var cfg Config
	if err := json.Unmarshal(data, &cfg); err != nil {
		return resetDefault()
	}
	return &cfg, nil
}