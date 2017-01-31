# Starter files for MP2
Use the following commands in your vagrant development environment to get this up and running
```bash
git clone https://github.com/uiuc-web-programming/mp2_starter.git
cd mp2_starter
npm install
bower install
grunt compass:dev
grunt compass:foundation
grunt uglify
grunt
```

For MP2, you should edit the following:
- `public/index.html` - all files in the `public` folder will be served by the server
- `sass` folder - all sass files here will be compiled to `public/css/styles.css`
- `js` folder - all javascript files here will be uglified and put in `public/js/script.js`
- `public/lib/foundation/scss` - all scss files here will be compiled and put in `public/lib/foundation/css/foundation.css`

Also, if you have problems debugging your JavaScript due to uglification, you can disable it by commenting out line 46 of `gruntfile.js` and uncommenting line 47. Your final submission should work with uglification though.
