/*
** mrb_file_access.c - File access class
**
** Copyright (c) takumakume 2017
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"

#include <errno.h>
#include <unistd.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

mrb_value _file_access(mrb_state *mrb, const char *pathname, int mode)
{
  int ret;

  ret = access(pathname, mode);

  if (ret == -1) {
    switch (errno) {
      case ENOENT:  // A component of pathname does not exist or is a dangling symbolic link
      case EACCES:  // The access, or search permission is denied for one of the directories in the path prefix of pathname
      case ENOTDIR: // A component used as a directory in pathname is not, in fact, a directory
        return mrb_false_value();
      case ELOOP:
        mrb_raise(mrb, E_RUNTIME_ERROR, "Too many symbolic links were encountered in resolving pathname");
      case ENAMETOOLONG:
        mrb_raise(mrb, E_RUNTIME_ERROR, "pathname is too long");
      case EROFS:
        mrb_raise(mrb, E_RUNTIME_ERROR, "Write permission was requested for a access on a read-only accesssystem");
      case EFAULT:
        mrb_raise(mrb, E_RUNTIME_ERROR, "pathname points outside your accessible address space");
      case EINVAL:
        mrb_raise(mrb, E_RUNTIME_ERROR, "mode was incorrectly specified");
      case EIO:
        mrb_raise(mrb, E_RUNTIME_ERROR, "An I/O error occurred");
      case ENOMEM:
        mrb_raise(mrb, E_RUNTIME_ERROR, "Insufficient kernel memory was available");
      case ETXTBSY:
        mrb_raise(mrb, E_RUNTIME_ERROR, "Write access was requested to an executable which is being executed");
    }
    return mrb_false_value();
  }
  return mrb_true_value();
}


mrb_value mrb_file_access_exist(mrb_state *mrb, mrb_value self)
{
  mrb_value pathname;
  mrb_get_args(mrb, "S", &pathname);
  return _file_access(mrb, mrb_string_value_cstr(mrb, &pathname), F_OK);
}

mrb_value mrb_file_access_readable(mrb_state *mrb, mrb_value self)
{
  mrb_value pathname;
  mrb_get_args(mrb, "S", &pathname);
  return _file_access(mrb, mrb_string_value_cstr(mrb, &pathname), R_OK);
}

mrb_value mrb_file_access_writable(mrb_state *mrb, mrb_value self)
{
  mrb_value pathname;
  mrb_get_args(mrb, "S", &pathname);
  return _file_access(mrb, mrb_string_value_cstr(mrb, &pathname), W_OK);
}

mrb_value mrb_file_access_executable(mrb_state *mrb, mrb_value self)
{
  mrb_value pathname;
  mrb_get_args(mrb, "S", &pathname);
  return _file_access(mrb, mrb_string_value_cstr(mrb, &pathname), X_OK);
}

void mrb_mruby_file_access_gem_init(mrb_state *mrb)
{
  struct RClass *io     = mrb_define_class(mrb, "IO", mrb->object_class);
  struct RClass *file   = mrb_define_class(mrb, "File", io);
  struct RClass *access = mrb_define_class_under(mrb, file, "Access", mrb->object_class);

  mrb_define_class_method(mrb, access, "exist?",      mrb_file_access_exist,      MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, access, "exists?",     mrb_file_access_exist,      MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, access, "readable?",   mrb_file_access_readable,   MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, access, "writable?",   mrb_file_access_writable,   MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, access, "executable?", mrb_file_access_executable, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_file_access_gem_final(mrb_state *mrb)
{
}
