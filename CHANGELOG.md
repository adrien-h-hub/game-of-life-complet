# Changelog - Conway's Game of Life

All notable changes to this project will be documented in this file.

## [1.1.0] - 2025-12-01

### Added
- 🎨 **8 Beautiful Color Themes**: Neon, Ocean, Forest, Sunset, Lavender, Rainbow, Fire, Ice
- ⏮️ **Time Travel System**: Rewind (←) and Forward (→) through generation history
- ⏸️ **Auto-Pause on Stable Patterns**: Automatically pauses when detecting oscillators or still lifes
- 🔍 **Pattern Detection System**: Recognizes classic patterns (Block, Blinker, Glider, etc.)
- 🎲 **Enhanced Random Generator**: Press R for random 3×3 pattern (4-9 cells) in center
- 📊 **Advanced Statistics Panel**: Generation, population, births/deaths, max/min/avg population
- 🗺️ **Mini-Map**: Navigate large grids with ease
- 📖 **Interactive Help Overlay**: Press H for control reference
- 🎨 **Cell Age Visualization**: See how long cells have been alive with color gradients
- 📈 **FPS Counter**: Real-time performance monitoring
- ⚡ **Speed Control**: Adjust simulation speed with +/- keys
- 🖱️ **Enhanced Mouse Controls**: Pan with right-drag, zoom with scroll wheel
- 🎯 **Generation Reset**: Generation counter resets to 0 when using time travel or pressing R

### Changed
- **R key behavior**: Now generates random 3×3 pattern and resets generation to 0
- **Improved UI**: Modern dark theme with semi-transparent panels
- **Better performance**: Optimized rendering with SFML 3.0
- **Enhanced grid**: Smoother visualization with toggleable grid lines

### Fixed
- Window positioning and camera offset optimization (-243px left shift)
- Proper handling of grid boundaries
- Memory leaks in history management
- UI overlay rendering issues

## [1.0.0] - 2025-11-28

### Added
- 🎮 **Core Game of Life Implementation**: Conway's rules with 8-neighbor topology
- 🖼️ **SFML 3.0 Graphics**: Beautiful real-time rendering
- 🎨 **Multiple Themes**: Initial theme system
- 🖱️ **Mouse Interaction**: Click to draw cells
- ⌨️ **Keyboard Controls**: Play/pause, step, clear, reset
- 📊 **Basic Statistics**: Generation count, population
- 🏗️ **Clean OOP Architecture**: Grid, GameEngine, Renderer classes
- 📐 **SOLID Principles**: Proper separation of concerns
- 📝 **Console Mode**: Text-based version for debugging
- 📚 **Documentation**: Basic README and code comments

### Technical
- C++20 with modern features
- SFML 3.0 for graphics
- Make build system
- Cross-platform support (Windows, Linux, macOS)
- Modular architecture with clear interfaces

---

## Version History

| Version | Date | Highlights |
|---------|------|------------|
| 1.1.0 | 2025-12-01 | Time travel, auto-pause, 8 themes, pattern detection |
| 1.0.0 | 2025-11-28 | Initial release with core features |

---

## Upcoming Features (Roadmap)

### Version 1.2.0 (Planned)
- [ ] Custom pattern library import/export
- [ ] Save/load simulation states
- [ ] Recording and GIF export
- [ ] Sound effects (optional)
- [ ] Advanced statistics graphs
- [ ] Custom grid sizes via UI
- [ ] Multi-grid support (multiple simulations)

### Version 1.3.0 (Planned)
- [ ] Network multiplayer (collaborative patterns)
- [ ] Pattern competition mode
- [ ] AI pattern generator
- [ ] 3D visualization mode
- [ ] Performance profiler
- [ ] Plugin system

---

## Bug Reports & Feature Requests

Please report bugs and request features via:
- GitHub Issues: https://github.com/yourusername/GameOfLife/issues
- Email: your.email@example.com

---

## Contributors

Special thanks to all contributors who help improve this project!

- **[Your Name]** - Initial development and maintenance

See [CONTRIBUTING.md](docs/CONTRIBUTING.md) for how to contribute.

---

**Current Version**: 1.1.0  
**Last Updated**: December 1, 2025  
**Status**: Active Development 🚀
