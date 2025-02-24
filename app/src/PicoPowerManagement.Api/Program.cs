using Microsoft.AspNetCore.Hosting.StaticWebAssets;

namespace PicoPowerManagement.Api
{
	public class Program
	{
		public static async Task Main(string[] args)
		{
			var builder = WebApplication.CreateBuilder(args);

			StaticWebAssetsLoader.UseStaticWebAssets(builder.Environment, builder.Configuration); // Corrected parameters


			builder.Services.AddProblemDetails();

			var app = builder.Build();

			app.UseWebAssemblyDebugging(); // Corrected method name
			app.UseDeveloperExceptionPage();
			app.UseStatusCodePages();
			app.UseBlazorFrameworkFiles();
			app.UseStaticFiles();
			app.MapFallbackToFile("index.html");
			app.Run();
		}
	}
}
