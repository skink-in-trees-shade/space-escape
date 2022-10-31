from conans import ConanFile, CMake

class SpaceEscape(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	generators = "cmake"

	def requirements(self):
		self.requires("sdl/2.24.1")
		self.requires("sdl_image/2.0.5")
		self.requires("sdl_mixer/2.0.4")
		self.requires("entityx/1.3.0")
		self.requires("box2d/2.4.1")
		self.requires("fruit/3.6.0")
		self.requires("zlib/1.2.13", override = True)

	def configure(self):
		self.options["sdl_image"].bmp = False
		self.options["sdl_image"].gif = False
		self.options["sdl_image"].lbm = False
		self.options["sdl_image"].pcx = False
		self.options["sdl_image"].pnm = False
		self.options["sdl_image"].svg = False
		self.options["sdl_image"].tga = False
		self.options["sdl_image"].xcf = False
		self.options["sdl_image"].xpm = False
		self.options["sdl_image"].xv = False
		self.options["sdl_image"].with_libjpeg = False
		self.options["sdl_image"].with_libtiff = False
		self.options["sdl_image"].with_libpng = True
		self.options["sdl_image"].with_libwebp = False
		if self.settings.os == "Macos":
			self.options["sdl_image"].imageio = False

		self.options["sdl_mixer"].cmd = False
		self.options["sdl_mixer"].flac = False
		self.options["sdl_mixer"].fluidsynth = False
		self.options["sdl_mixer"].mad = False
		self.options["sdl_mixer"].mikmod = False
		self.options["sdl_mixer"].modplug = False
		self.options["sdl_mixer"].mpg123 = False
		self.options["sdl_mixer"].ogg = False
		self.options["sdl_mixer"].opus = False
		self.options["sdl_mixer"].wav = True
		if self.settings.os == "Linux":
			self.options["sdl_mixer"].tinymidi = False
		if self.settings.os == "Windows" or self.settings.os == "Macos":
			self.options["sdl_mixer"].nativemidi = False

		self.options["fruit"].use_boost = False

	def generate(self):
		cmake = CMake(self)
		self.run("cmake -B %s -DCMAKE_BUILD_TYPE=%s" % (self.install_folder, cmake.build_type), cwd = self.source_folder)

	def build(self):
		cmake = CMake(self)
		self.run("cmake --build %s --config %s" % (self.install_folder, cmake.build_type), cwd = self.source_folder)