module.exports = function(grunt) {
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-compass');
  grunt.loadNpmTasks('grunt-express-server');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.initConfig({
    clean: ["public/js"],
    uglify: {
      my_target: {
        options: {
          mangle: false
        },
        files: {
          'public/js/script.js': ['js/script.js'],
          'public/js/controllers.js': ['js/controllers.js'],
          'public/js/app.js': ['js/app.js'],
          'public/js/services.js': ['js/services.js'],
	  'public/js/event/app.js':['js/event/app.js'],
	  'public/js/user/app/js':['js/user/app.js'],
	  'public/js/utils.js':['js/utils.js']
        } //files
      } //my_target
    }, //uglify
    copy: {
      files: {
            expand : true,
            dest   : 'public/js',
            cwd    : 'js',
            src    : [
              '**/*.js',
	      '**/event/*.js',
	      '**/user/*.js',
	      '**/setting/*.js',
	      '**/auth/*.js',
	      '**/login/*.js'
            ]
      }
    },
    compass: {
      dev: {
        options: {
          config: 'compass_config.rb'
        } //options
      }, //dev
      foundation: {
        options: {
          config: 'compass_foundation_config.rb'
        } //options
      } //foundation

    }, //compass
    watch: {
      options: { livereload: true },
      scripts: {
        files: ['js/*.js', 'js/event/*.js','js/user/*.js','js/setting/*.js','js/auth/*.js'],
        //tasks: ['clean','uglify'],
        tasks: ['copy']
      }, //script
      sass: {
        files: ['sass/*.scss'],
        tasks: ['compass:dev','compass:foundation']
      }, //sass
      sass_foundation: {
        files: ['public/foundation/scss/foundation.scss','public/foundation/scss/foundation/*.scss','public/foundation/scss/foundation/components/*.scss', 'public/foundation/js/foundation/*.js'],
        tasks: ['compass:foundation']
      }, //sass_foundation
      html: {
        files: ['public/*.html', 'public/partials/*.html']
      }
    }, //watch
    express: {
      options: {
        // Override defaults here
      },
      dev: {
        options: {
          script: 'app.js'
        }
      }
  }
  }) //initConfig
  grunt.registerTask('default', ['express:dev', 'watch']);
} //exports
