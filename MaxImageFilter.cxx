#include <iostream>
#include <itkImage.h>
#include <itkMaximumImageFilter.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include "MaxImageFilterCLP.h"


int main(int argc, char *argv[])
{
  PARSE_ARGS;
  std::cout<<filename1<<std::endl;
  std::cout<<filename2<<std::endl;
  if( !filename1.empty() && !filename2.empty())
  {
    std::cout<<"MaximumImageFilter"<<std::endl;
    typedef unsigned char PixelType;
    const unsigned int Dim=3;

    typedef itk::Image <PixelType, Dim> ImageType;
    typedef itk::ImageFileReader <ImageType> ReaderType;
    ReaderType::Pointer reader1 = ReaderType::New();
    ReaderType::Pointer reader2 = ReaderType::New();
    reader1->SetFileName(filename1.c_str());
    reader2->SetFileName(filename2.c_str());
    //reader1->Update();
    //reader2->Update();
    ImageType::Pointer image1= reader1->GetOutput();
    ImageType::Pointer image2= reader2->GetOutput();

    typedef itk::MaximumImageFilter<ImageType, ImageType, ImageType> MaxType;
    MaxType::Pointer maxfilter = MaxType::New();
    maxfilter->SetInput(image1);
    maxfilter->SetInput2(image2);
    //maxfilter->Update();
    ImageType::Pointer image3= maxfilter->GetOutput();

    typedef itk::ImageFileWriter <ImageType> WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputfilename.c_str());
    writer->SetInput(image3);
    try
      {
	writer->Update();
      }
    catch (itk::ExceptionObject & err)
      {
	std::cerr<<"Exception object caught!"<<std::endl;
	std::cerr<<err<<std::endl;
      }
  }

  return 0;
}
