MRuby::Gem::Specification.new('mruby-file-access') do |spec|
  spec.license = 'MIT'
  spec.authors = 'takumakume'

  test_files = { readable: 0400, writable: 0200, executable: 0100 }

  task :test => test_files.map{|k,_| "#{build.build_dir}/../file-access-fixtures/#{k}" }
  test_files.each do |k, v|
    file "#{build.build_dir}/../file-access-fixtures/#{k}" do |t|
      sh "mkdir -p #{File.dirname t.name}"
      sh "touch #{t.name}"
      sh "chmod #{v.to_s(8)} #{t.name}"
    end
  end
end
