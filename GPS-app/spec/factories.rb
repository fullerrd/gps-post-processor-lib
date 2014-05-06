FactoryGirl.define do
  factory :user do
    name     "Dominic Fuller-Rowell"
    email    "dominic.fuller-rowell@colorado.edu"
    password "lemonhead"
    password_confirmation "lemonhead"
  end
end