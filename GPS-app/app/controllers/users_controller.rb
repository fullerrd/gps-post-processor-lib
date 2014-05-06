class UsersController < ApplicationController
	def show
    @user = User.find(params[:id])
  end
  def new
  	@user = User.new
  end
  def create
    @user = User.new(user_params)
    if @user.save
      sign_in @user
      flash[:success] = "Welcome to the Differential Correction Service web-app!"
      redirect_to @user
    else
      render 'new'
    end
  end
  def postprocess
    @user = User.find(params[:id])
  end
  def edit
    @user = User.find(params[:id])
  end

  def update
    @user = User.find(params[:id])
    if @user.update_attributes(user_params)
      # Handle a successful update.
    else
      render 'edit'
    end
  end
  def upload
    @user = User.find(params[:id])
    uploaded_io = params[:gpsdatafile]
    if (uploaded_io != nil)
      File.open(Rails.root.join('uploads', uploaded_io.original_filename), 'wb') do |file|
        file.write(uploaded_io.read)
      end
      #flash[:success] = "File submitted. Please wait for prompt to download your corrected data."      
      redirect_to root_path
      sleep(4.seconds)
      system('./GPS_CPP/correctCsv uploads/' + uploaded_io.original_filename)
      #send_file(Rails.root.join('uploads', uploaded_io.original_filename),filename: "corrected_"+uploaded_io.original_filename,type: "application/csv")
      send_file(Rails.root.join('uploads', "corrected.csv"),filename: "corrected_"+uploaded_io.original_filename,type: "application/csv")
    else
      flash[:failure] = "Please select a file before submitting."
      redirect_to @user
    end
  end
  def download
    send_file("#{Rails.root}/uploads/your_file.pdf",
    filename: "your_custom_file_name.pdf",
    type: "application/pdf")
  end
  private
    def user_params
      params.require(:user).permit(:name, :email, :password,
                                   :password_confirmation)
    end
  end

