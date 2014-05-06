require 'spec_helper'

describe "Static pages" do
  subject { page }

  shared_examples_for "all static pages" do
    it { should have_selector('h1', text: heading) }
    it { should have_title(full_title(page_title)) }
  end

  describe "Home page" do
    before { visit root_path}
    let(:heading)    { 'Differential GPS Correction Service' }
    let(:page_title) { '' }
    it { should have_title('| Home') }
    it_should_behave_like "all static pages"
  end

  describe "Help page" do
    before { visit help_path }
    let(:heading)    { 'Help' }
    let(:page_title) { 'Help' }
    it_should_behave_like "all static pages"
  end

  describe "About page" do
    before { visit about_path }
    let(:heading)    { 'About Differential GPS Corrections'}
    let(:page_title) { 'About Differential GPS Corrections' }
    it_should_behave_like "all static pages"
    it { should have_css('img', text: "uml - class diagram.png") }
    it { should have_css('img', text: "architecture_diagram.png") }
  end

  describe "Contact page" do
    before { visit contact_path }
    let(:heading)    { 'Contact'}
    let(:page_title) { 'Contact' }

    it { should have_selector('h1', text: 'Contact') }
    it_should_behave_like "all static pages"
  end


end