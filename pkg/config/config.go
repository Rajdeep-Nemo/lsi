package config

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

// Struct to hold values
type Config struct {
	ShowIcons bool
	ShowColor bool
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

// Reads/parses the config and resets it if the file is corrupted
func LoadConfig() (*Config, error) {
	if err := initConfig(); err != nil {
		return nil, err
	}

	path, err := configPath()
	if err != nil {
		return nil, err
	}

	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}

	lines := strings.SplitN(string(data), "\n", 2)

	// Helper function to reset the file with defaults
	resetConfig := func() (*Config, error) {
		err := os.WriteFile(path, []byte(defaultConfig), 0644)
		if err != nil {
			return nil, err
		}
		return &Config{ShowIcons: true, ShowColor: true}, nil
	}

	cfg := &Config{}
	parsedIcons := false
	parsedColor := false

	for _, line := range lines {
		if strings.TrimSpace(line) == "" {
			continue
		}

		parts := strings.SplitN(line, "=", 2)
		if len(parts) != 2 {
			return resetConfig()
		}

		key := strings.TrimSpace(parts[0])
		value := strings.TrimSpace(parts[1])

		if value != "true" && value != "false" {
			return resetConfig()
		}

		switch key {
		case "icons":
			cfg.ShowIcons = (value == "true")
			parsedIcons = true
		case "color":
			cfg.ShowColor = (value == "true")
			parsedColor = true
		default:
			return resetConfig()
		}
	}

	if !parsedIcons || !parsedColor {
		return resetConfig()
	}

	return cfg, nil
}

func SaveConfig(cfg *Config) error {
	path , err := configPath()
	if err != nil {
		return err
	}

	content := 
}
