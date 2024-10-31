from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake, CMakeDeps, CMakeToolchain

class SpaceEscape(ConanFile):
	name = "space-escape"
	version = "0.1"
	settings = "os", "compiler", "build_type", "arch"

	def requirements(self):
		self.requires("sdl/2.30.8", override = True)
		self.requires("sdl_image/2.6.3")
		self.requires("sdl_mixer/2.8.0")
		self.requires("entityx/1.3.0")
		self.requires("box2d/2.4.1")
		self.requires("fruit/3.7.1")

	def configure(self):
		self.options["sdl_image"].with_libpng = True
		self.options["sdl_image"].bmp = False
		self.options["sdl_image"].gif = False
		self.options["sdl_image"].lbm = False
		self.options["sdl_image"].pcx = False
		self.options["sdl_image"].pnm = False
		self.options["sdl_image"].svg = False
		self.options["sdl_image"].tga = False
		self.options["sdl_image"].qoi = False
		self.options["sdl_image"].xcf = False
		self.options["sdl_image"].xpm = False
		self.options["sdl_image"].xv = False
		self.options["sdl_image"].with_libjpeg = False
		self.options["sdl_image"].with_libtiff = False
		self.options["sdl_image"].with_libwebp = False
		self.options["sdl_image"].with_avif = False
		self.options["sdl_image"].with_jxl = False
		if self.settings.os == "Macos":
			self.options["sdl_image"].imageio = False
		if self.settings.os == "Windows":
			self.options["sdl_image"].wic = False

		self.options["sdl_mixer"].wav = True
		self.options["sdl_mixer"].cmd = False
		self.options["sdl_mixer"].flac = False
		self.options["sdl_mixer"].mpg123 = False
		self.options["sdl_mixer"].mad = False
		self.options["sdl_mixer"].ogg = False
		self.options["sdl_mixer"].opus = False
		self.options["sdl_mixer"].mikmod = False
		self.options["sdl_mixer"].modplug = False
		if self.settings.os == "Macos" or self.settings.os == "Windows":
			self.options["sdl_mixer"].nativemidi = False
		if self.settings.os == "Linux":
			self.options["sdl_mixer"].tinymidi = False

		self.options["fruit"].with_boost = False

	def build_requirements(self):
		self.tool_requires("cmake/[>=3.15 <4]")

	def generate(self):
		toolchain = CMakeToolchain(self)
		toolchain.user_presets_path = False
		toolchain.generate()

		deps = CMakeDeps(self)
		deps.generate()

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def package(self):
		cmake = CMake(self)
		cmake.install()

	def layout(self):
		cmake_layout(self)
