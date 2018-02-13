dir = "./build/file-access-fixtures/"

assert('File::Access') do
  assert_equal(Class, File::Access.class)
end

assert('File::Access.exist?') do
  assert_true(File::Access.exist?("#{dir}readable"))
  assert_false(File::Access.exist?("#{dir}notfound"))
end

assert('File::Access.exists?') do
  assert_true(File::Access.exists?("#{dir}readable"))
end

assert('File::Access.readable?') do
  assert_true(File::Access.readable?("#{dir}readable"))
end

assert('File::Access.writable?') do
  assert_true(File::Access.writable?("#{dir}writable"))
  assert_false(File::Access.writable?("#{dir}readable"))
end

assert('File::Access.executable?') do
  assert_true(File::Access.executable?("#{dir}executable"))
  assert_false(File::Access.executable?("#{dir}readable"))
  assert_false(File::Access.executable?("#{dir}writable"))
end
