def fake_makefile
  File.open(File.join(File.dirname(__FILE__), "Makefile"), "w") {|f|
    f.puts %[install:\n\techo "Nada."]
    f.puts %[clean:\n\techo "Nada."]
    f.puts %[distclean:\n\techo "Nada."]
  }
end

def mri_2?
  defined?(RUBY_ENGINE) && RUBY_ENGINE == "ruby" &&
    RUBY_VERSION =~ /^2/
end

  
if mri_2?
  require 'mkmf'
  create_makefile('debug_inspector')
else
  fake_makefile
end
