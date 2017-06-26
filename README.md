# mruby-file-access   [![Build Status](https://travis-ci.org/takumakume/mruby-file-access.svg?branch=master)](https://travis-ci.org/takumakume/mruby-file-access)

accsess(2) for mruby.

This is a fast file check method.

## install by mrbgems

- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'takumakume/mruby-file-access'
end
```
## methods

```ruby
File::Access.exist?(pathname) # or File::Access.exists?(pathname)
File::Access.readable?(pathname)
File::Access.writable?(pathname)
File::Access.executable?(pathname)
```

## benchmark

- using stat(2)

  ```ruby
  1000000.times do
    File.exist?("samplefile")
  end
  ```

  ```shell
  # time mruby stat.rb
  mruby stat.rb  1.53s user 0.31s system 99% cpu 1.857 total
  ```

- using access(2)

  ```ruby
  1000000.times do
    File::Access.exist?("samplefile")
  end
  ```

  ```sh
  # time mruby access.rb
  mruby access.rb  0.61s user 0.40s system 98% cpu 1.026 total
  ```

## License

under the MIT License:
- see LICENSE file
