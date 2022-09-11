from conans import ConanFile, CMake

class SpaceEscape(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	requires = (
		"sdl/2.24.0",
		"sdl_image/2.0.5",
		"sdl_mixer/2.0.4",
		"entityx/1.3.0",
		"box2d/2.4.1",
		"fruit/3.6.0",
	)
	generators = "cmake"
	default_options = {
		"sdl_image:bmp": False,
		"sdl_image:gif": False,
		"sdl_image:lbm": False,
		"sdl_image:pcx": False,
		"sdl_image:pnm": False,
		"sdl_image:svg": False,
		"sdl_image:tga": False,
		"sdl_image:xcf": False,
		"sdl_image:xpm": False,
		"sdl_image:xv": False,
		"sdl_image:with_libjpeg": False,
		"sdl_image:with_libtiff": False,
		"sdl_image:with_libpng": True,
		"sdl_image:with_libwebp": False,
		"sdl_mixer:cmd": False,
		"sdl_mixer:flac": False,
		"sdl_mixer:fluidsynth": False,
		"sdl_mixer:mad": False,
		"sdl_mixer:mikmod": False,
		"sdl_mixer:modplug": False,
		"sdl_mixer:mpg123": False,
		"sdl_mixer:ogg": False,
		"sdl_mixer:opus": False,
		"sdl_mixer:wav": True,
		"fruit:use_boost": False,
	}

	def configure(self):
		if self.settings.os == "Linux":
			self.options["sdl_mixer"].tinymidi = False
		if self.settings.os == "Windows":
			self.options["sdl_mixer"].nativemidi = False
		if self.settings.os == "Macos":
			self.options["sdl_image"].imageio = False
			self.options["sdl_mixer"].nativemidi = False