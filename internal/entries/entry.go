package entries

import (
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"time"
)

// Holds information about each entry in a directory
type Entry struct {
	Name      string
	Extension string
	Mode      fs.FileMode
	Size      int64
	ModTime   time.Time
	IsDir     bool
}

// Reads a directory without hidden files/dir
func GetVisibleEntries(path string) ([]Entry, error) {
	entries, err := GetAllEntries(path)
	if err != nil {
		return nil, err
	}
	result := FilterHidden(entries)
	return result, nil
}

// Reads a directory
func GetAllEntries(path string) ([]Entry, error) {
	entries, err := os.ReadDir(path)
	if err != nil {
		return nil, err
	}
	var result []Entry
	for _, e := range entries {
		info, err := e.Info()
		if err != nil {
			return nil, err
		}
		result = append(result, Entry{
			Name:      e.Name(),
			Extension: strings.ToLower(filepath.Ext(e.Name())),
			Mode:      info.Mode(),
			Size:      info.Size(),
			ModTime:   info.ModTime(),
			IsDir:     e.IsDir(),
		})
	}
	return result, nil
}

// Filter out hidden entries
func FilterHidden(entries []Entry) []Entry {
	var result []Entry
	for _, e := range entries {
		if strings.HasPrefix(e.Name, ".") {
			continue
		}
		result = append(result, e)
	}
	return result
}
